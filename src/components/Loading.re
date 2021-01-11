let str = React.string;
[@bs.module]
external loadingAnimation: string = "../assets/lotties/loading.json";

open Lottie;

[@react.component]
let make = () => {
  let animationOptions = {
    loop: true,
    autoplay: true,
    animationData: loadingAnimation,
    rendererSettings: {
      preserveAspectRatio: "xMidYMid slice",
    },
  };
  <Lottie options=animationOptions width=25 height=25 />;
};
