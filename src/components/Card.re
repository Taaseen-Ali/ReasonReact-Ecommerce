let str = React.string;

[@react.component]
let make = (~children=React.null, ~className="", ~label=React.null, ~onClick) => {
  <div onClick className={"relative m-0 p-0 " ++ className}>
    children
    <div
      className="absolute flex inset-0 m-0 bg-black text-white z-auto opacity-0 text-opacity-0 hover:opacity-50 hover:text-opacity-100">
      <div className="text-xl text-center m-auto align-middle"> label </div>
    </div>
  </div>;
};
