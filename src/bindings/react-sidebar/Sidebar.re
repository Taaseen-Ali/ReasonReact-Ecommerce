[@react.component] [@bs.module "react-sidebar"]
external make:
  (
    ~children: React.element,
    ~sidebar: React.element,
    ~_open: bool,
    ~onSetOpen: _ => 'a,
    ~touch: bool,
    ~pullRight: bool
  ) =>
  React.element =
  "default";
