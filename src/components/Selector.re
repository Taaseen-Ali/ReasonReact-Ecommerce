let str = React.string;

open ReactPureCarousel;
open ShopifyBuy.Types_;
open ShopifyBuy.Utils;

[@react.component]
let make = (~item) => {
  let options = item.options;
  let getSelectedItem = item.variants->getSelectedItemFromVariants;
  let (selected, setSelected) =
    React.useState(_ =>
      options->Belt.Array.map(opt =>
        {name: opt.name, value: opt.values[0].value}
      )
    );
  let selectedItem = getSelectedItem(selected);

  Js.log(selectedItem);

  <div
    className="flex flex-col m-0 md:flex-row md:m-20 justify-center md:space-x-32">
    <Carousel
      className="relative sm:w-full md:w-1/4"
      naturalSlideHeight=100
      naturalSlideWidth=75
      totalSlides={item.images->Belt.Array.length}>
      <Slider>
        {item.images
         ->Belt.Array.mapWithIndex((i, image) =>
             <Slide key={i->string_of_int} index=i>
               <ImageWithZoom src={image.src} />
             </Slide>
           )
         ->React.array}
      </Slider>
      <div
        className="flex flex-col absolute top-0 w-1/4 md:w-full md:relative md:flex-row md:border-t-4 md:border-black md:rounded-sm">
        {item.images
         ->Belt.Array.mapWithIndex((i, image) => {
             <Dot className="m-0 w-full" key={i->string_of_int} slide=i>
               <Card className="" onClick={_ => Js.log("hi")}>
                 <img src={image.src} />
               </Card>
             </Dot>
           })
         ->React.array}
      </div>
      <div className="flex justify-center">
        <ButtonBack className="m-4"> "Back"->str </ButtonBack>
        <ButtonNext className="m-4"> "Next"->str </ButtonNext>
      </div>
    </Carousel>
    <div
      className="flex flex-col p-8 md:border-2 md:border-black md:rounded-md">
      <p className="text-4xl"> item.title->str </p>
      <p className="text-2xl"> {("$" ++ selectedItem.price)->str} </p>
      {options
       ->Belt.Array.map(option =>
           <div
             className="flex my-4 mx-2 p-4 flex flex-col border-2 border-black rounded-md md:border-none"
             key={option.name}>
             <p className="text-l "> option.name->str </p>
             <div className="flex flex-wrap flex-row justify-center">
               {option.values
                ->Belt.Array.map(v =>
                    <button
                      className={
                        "p-2 m-4 rounded-md border-black hover:bg-gray-300 "
                        ++ (
                          switch ({name: option.name, value: v.value}) {
                          | _ as a when selected->Belt.Array.some(i => i == a) => "border-2"
                          | _ => ""
                          }
                        )
                      }
                      key={v.value}
                      onClick={_ =>
                        setSelected(state =>
                          state->Belt.Array.map(
                            fun
                            | {name: a} when a == option.name => {
                                name: option.name,
                                value: v.value,
                              }
                            | _ as i => i,
                          )
                        )
                      }>
                      v.value->str
                    </button>
                  )
                ->React.array}
             </div>
           </div>
         )
       ->React.array}
      <AddToCartButton itemId={selectedItem.id} />
    </div>
  </div>;
};
