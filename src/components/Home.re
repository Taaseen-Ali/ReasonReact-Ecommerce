let str = React.string;

open ShopifyBuy;
open ShopifyBuy.Types_;

[@react.component]
let make = () => {
  let (products, setProducts) = React.useState(_ => None);
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
    <div className="md:hidden flex p-2 w-full bg-black bg-opacity-50">
      <span
        className="inline-block text-center align-middle text-opacity-80 text-white mx-auto">
        "Short hold & drag over a product for overview"->str
      </span>
    </div>
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
