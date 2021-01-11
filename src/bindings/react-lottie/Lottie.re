type rendererSettings = {preserveAspectRatio: string};

type lottieOptions = {
  loop: bool,
  autoplay: bool,
  animationData: string,
  rendererSettings,
};

[@react.component] [@bs.module "react-lottie"]
external make:
  (~options: lottieOptions, ~width: int, ~height: int) => React.element =
  "default";
