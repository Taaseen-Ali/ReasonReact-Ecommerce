let str = React.string;
[@react.component]
let make = (~title, ~items=[||], ~img="") =>
  <div
    className="flex flex-col md:flex-row justify-center items-center p-8 md:p-2 bg-red-100 md:h-10 w-full">
    <div className="flex-1 self-center">
      {switch (img) {
       | "" => React.null
       | _ => <img src=img className="object-contain h-8" />
       }}
    </div>
    <p
      className="flex-1 self-center font-thin text-center text-l"
      onClick={_ => ReasonReactRouter.push("/")}>
      {title |> str}
    </p>
    <div className="flex-1 flex justify-end">
      {items
       ->Belt.Array.mapWithIndex((i, elem) =>
           <div
             key={i->string_of_int}
             className="flex items-center text-center h-full mx-4 my-4">
             elem
           </div>
         )
       ->React.array}
    </div>
  </div>;
