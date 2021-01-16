let str = React.string;
open ShopifyBuy.Types_;

[@react.component]
let make = (~item: item) =>
  <Card
    className="w-1/2 md:w-1/4"
    label={
      <div>
        <p> item.title->str </p>
        <p> {("$" ++ item.variants[0].price)->str} </p>
      </div>
    }
    onClick={_ => ReasonReactRouter.push("/product/" ++ item.id)}>
    {switch (item.images) {
     | [||] => <p> "No images available"->str </p>
     | _ => <img className="m-0 w-full" src={item.images[0].src} />
     }}
    <div className="md:hidden w-full h-10 text-left p-4 text-xs">
      item.title->str
    </div>
  </Card>;
