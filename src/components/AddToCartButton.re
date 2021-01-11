let str = React.string;
open ShopifyBuy.Types_;
open ShopifyBuy;
open ShopifyBuy.Utils;
open ShopContext.Actions;

[@react.component]
let make = (~itemId) => {
  let (client, _, _, dispatch) = ShopContext.useShop();
  let (checkout, setCheckout) = React.useState(_ => None);
  React.useEffect0(() => {
    client->getCheckout
    |> Js.Promise.then_(checkout => {
         Js.log(checkout);
         setCheckout(_ => Some(checkout));
         Js.Promise.resolve(checkout);
       })
    |> ignore;
    None;
  });

  let toAdd = {variantId: itemId, quantity: 1};

  switch (checkout) {
  | None => <button> "Loading cart..."->str </button>
  | Some(i) =>
    <button
      className="justify-self-stretch text-l border-2 border-black rounded-md p-4 mx-2 my-4 hover:bg-gray-300"
      onClick={_ => {
        client.checkout->addLineItems(i.id, toAdd)
        |> Js.Promise.then_(v => {
             dispatch(UpdateCart);
             dispatch(ToggleCart(true));
             Js.log("here");
             Js.log(v);
             Js.Promise.resolve();
           })
        |> ignore
      }}>
      "Add to cart"->str
    </button>
  };
};
