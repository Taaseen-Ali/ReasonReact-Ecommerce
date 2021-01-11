let str = React.string;
open ShopifyBuy.Types_;
open ShopifyBuy;

[@react.component]
let make = (~id) => {
  let (client, _, _, _) = ShopContext.useShop();
  let (item, setItem) = React.useState(_ => None);
  React.useEffect0(() => {
    client.product->fetch(id)
    |> Js.Promise.then_(item => {
         setItem(_ => Some(item));
         Js.Promise.resolve();
       })
    |> ignore;
    None;
  });

  switch (item) {
  | None => <Loading />
  | Some(item) => <div> <Selector item /> </div>
  };
};
