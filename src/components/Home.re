let str = React.string;

open ShopifyBuy;

[@react.component]
let make = () => {
  let (products: option(array(ShopifyBuy.Types_.item)), setProducts) =
    React.useState(_ => None);
  let (client, _, _, _) = ShopContext.useShop();

  React.useEffect0(() => {
    client.product->fetchAll
    |> Js.Promise.then_(value => {
         setProducts(_ => Some(value));
         Js.Promise.resolve();
       })
    |> ignore;
    None;
  });

  <div className="flex flex-wrap">
    {switch (products) {
     | None => [|<Loading key="loading" />|]
     | Some([||]) => [|
         <p key="none" className="w-full text-center">
           "No products at this time"->str
         </p>,
       |]
     | Some(products) =>
       products->Belt.Array.map(p => <ItemCard key={p.id} item=p />)
     }}
    ->React.array
  </div>;
};
