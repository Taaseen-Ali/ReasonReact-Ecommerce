let str = React.string;

open ShopifyBuy.Types_;
open ShopifyBuy.Utils;
open ShopifyBuy;

[@react.component]
let make = () => {
  let (client, cart, checkoutLink, dispatch) = ShopContext.useShop();
  let (loadingRemoval, setLoadingRemoval) = React.useState(_ => false);

  Js.log(cart);
  React.useEffect0(() => {
    dispatch(UpdateCart);
    None;
  });

  <div
    className="relative flex flex-col items-stretch bg-white min-h-screen py-16 px-8 md:p-16 ">
    {loadingRemoval
       ? <div className="absolute top-0 right-0 m-8"> <Loading /> </div>
       : React.null}
    <button
      className="absolute flex justify-center items-center bg-white  border-black rounded-md h-6 w-6 top-0 left-0 m-8"
      onClick={_ => dispatch(ToggleCart(false))}>
      "X"->str
    </button>
    <div className="mx-24 md:mx-48 text-2xl text-center"> "Cart"->str </div>
    <div className="my-8">
      {switch (cart) {
       | [||] =>
         [|
           <div key="empty-cart" className="">
             "Add stuff to your cart foo"->str
           </div>,
         |]
         ->React.array
       | _ =>
         cart
         ->Belt.Array.map(i =>
             <div
               className="relative flex flex-row items-center justify-between"
               key={i.title ++ i.variant.title}>
               <div className="relative">
                 <img className="m-4 w-16" src={i.variant.image.src} />
                 <div
                   className="absolute flex justify-center items-center bg-white border-2 border-black rounded-md h-6 w-6 pt-full top-0 right-0 m-2">
                   {i.quantity->string_of_int->str}
                 </div>
               </div>
               <div className="flex flex-col justify-center text-center mx-0">
                 <p className="text-l px-2"> i.title->str </p>
                 <p className="text-sm px-2"> i.variant.title->str </p>
               </div>
               <p className="text-sm"> {("$" ++ i.variant.price)->str} </p>
               <button
                 onClick={_ => {
                   client
                   |> getCheckout
                   |> Js.Promise.then_(checkout => {
                        Js.Promise.resolve(checkout.id)
                      })
                   |> Js.Promise.then_(id => {
                        setLoadingRemoval(_ => true);

                        client.checkout->removeLineItems(id, [|i.id|]);
                      })
                   |> Js.Promise.then_(_ => {
                        setLoadingRemoval(_ => false);
                        dispatch(UpdateCart);
                        Js.Promise.resolve();
                      })
                   |> ignore
                 }}
                 className="absolute flex justify-center items-center bg-white h-6 w-6 pt-full top-0 right-0">
                 "X"->str
               </button>
             </div>
           )
         ->React.array
       }}
    </div>
    {switch (checkoutLink, cart) {
     | (None, _) => <button> "Loading Checkout"->str </button>
     | (Some(_), [||]) => React.null
     | (Some(link), _) =>
       <button
         className="w-auto border-2 border-black text-xl rounded-md p-2"
         onClick={_ => Window.openLink(link, "_blank")}>
         "Checkout"->str
       </button>
     }}
  </div>;
};
