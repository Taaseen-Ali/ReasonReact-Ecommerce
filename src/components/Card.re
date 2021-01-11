let str = React.string;

[@react.component]
let make = (~children=React.null, ~className="", ~label=React.null, ~onClick) => {
  <div onClick className={"relative m-0 p-0 w-1/2 md:w-1/4" ++ className}>
    children
    <div
      className="absolute top-0 m-0 w-full h-full bg-black text-white z-auto opacity-0 text-opacity-0 hover:opacity-50 hover:text-opacity-100 table text-center">
      <div className="text-xl table-cell align-middle"> label </div>
    </div>
  </div>;
};
