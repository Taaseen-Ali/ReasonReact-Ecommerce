let str = React.string;
[@bs.module] external cartImg: string = "../assets/images/cart.png";
[@bs.val] external publicUrl: string = "process.env.PUBLIC_URL";
open ShopifyBuy.Types_;
open ShopifyBuy.Utils;

type state = {isOpen: bool};

[@react.component]
let make = () => {
  open ShopContext.Actions;

  let url = ReasonReactRouter.useUrl();

  let (cart, setCart) = React.useState(_ => [||]);
  let (checkoutLink, setCheckoutLink) = React.useState(_ => None);
  let updateCart = () => {
    ShopContext.client
    |> getCheckout
    |> Js.Promise.then_(checkout => {
         setCart(_ => checkout.lineItems);
         setCheckoutLink(_ => Some(checkout.webUrl));
         Js.Promise.resolve();
       })
    |> ignore;
  };

  let (isOpen, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | ToggleCart(isOpen) =>
          updateCart();
          isOpen;
        | UpdateCart =>
          updateCart();
          state;
        },
      false,
    );

  let redirectHome = () => {
    ReasonReactRouter.push("/");
    React.null;
  };
  <ShopProvider value=(ShopContext.client, cart, checkoutLink, dispatch)>
    <Sidebar
      pullRight=true
      touch=true
      sidebar={<Cart />}
      _open=isOpen
      onSetOpen={() => dispatch(ToggleCart(!isOpen))}>
      <Navbar
        title="CremeNYC"
        items=[|
          <img
            className="h-6"
            src=cartImg
            onClick={_ => dispatch(ToggleCart(!isOpen))}
          />,
        |]
      />
      {switch (url.path) {
       | [] => <Home />
       | ["product"] => redirectHome()
       | ["product", id] => <ProductPage id />
       | _ => redirectHome()
       }}
    </Sidebar>
  </ShopProvider>;
};
