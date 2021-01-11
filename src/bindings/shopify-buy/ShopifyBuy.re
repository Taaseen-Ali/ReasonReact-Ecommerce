module Types_ = {
  type storeCredentials = {
    storefrontAccessToken: string,
    domain: string,
  };

  type image = {
    id: string,
    src: string,
  };

  type optionValue = {value: string};

  type option = {
    name: string,
    values: array(optionValue),
  };

  type variantOption = {
    name: string,
    value: string,
  };

  type variant = {
    title: string,
    image,
    id: string,
    price: string,
    _type: string,
    selectedOptions: array(variantOption),
  };

  type item = {
    title: string,
    id: string,
    images: array(image),
    variants: array(variant),
    options: array(option),
  };

  type shopifyAPI;

  type lineItem = {
    id: string,
    title: string,
    variant,
    quantity: int,
  };

  type addItem = {
    variantId: string,
    quantity: int,
  };

  type checkoutState = {
    id: string,
    lineItems: array(lineItem),
    webUrl: string,
  };

  type product;
  type checkout;
  type client = {
    product,
    checkout,
  };
};

open Types_;

[@bs.send]
external fetchAll: product => Js.Promise.t(array(item)) = "fetchAll";

[@bs.send] external fetch: (product, string) => Js.Promise.t(item) = "fetch";

[@bs.send]
external create: checkout => Js.Promise.t(checkoutState) = "create";

[@bs.send]
external addLineItems:
  (checkout, string, addItem) => Js.Promise.t(checkoutState) =
  "addLineItems";

[@bs.send]
external removeLineItems:
  (checkout, string, array(string)) => Js.Promise.t(checkoutState) =
  "removeLineItems";

[@bs.send]
external fetchCheckout: (checkout, string) => Js.Promise.t(checkoutState) =
  "fetch";

[@bs.send]
external buildClient: (shopifyAPI, storeCredentials) => client = "buildClient";

[@bs.module] external shopifyBuy: shopifyAPI = "shopify-buy";

module Utils = {
  let getVariantsWith = (variants: array(variant), option: variantOption) => {
    variants->Belt.Array.keep(var =>
      var.selectedOptions
      ->Belt.Array.some(o => {name: o.name, value: o.value} == option)
    );
  };

  let getSelectedItemFromVariants =
      (variants: array(variant), options: array(variantOption)) => options->Belt.Array.reduce(
                                                                    variants,
                                                                    getVariantsWith,
                                                                    )[0];
  let saveCheckoutId = id => {
    Dom.Storage.(localStorage |> setItem("checkout_id", id));
  };

  let getCheckout = client => {
    Dom.Storage.(
      localStorage
      |> getItem("checkout_id")
      |> (
        fun
        | None =>
          client.checkout->create
          |> Js.Promise.then_(checkout => {
               saveCheckoutId(checkout.id);
               Js.Promise.resolve(checkout);
             })
        | Some(id) => client.checkout->fetchCheckout(id)
      )
    );
  };
};
