[%bs.raw {|require('pure-react-carousel/dist/react-carousel.es.css')|}];

module Carousel_ = {
  [@react.component] [@bs.module "pure-react-carousel"]
  external make:
    (
      ~children: React.element,
      ~className: string,
      ~naturalSlideWidth: int,
      ~naturalSlideHeight: int,
      ~totalSlides: int
    ) =>
    React.element =
    "CarouselProvider";
};

module ButtonNext_ = {
  [@react.component] [@bs.module "pure-react-carousel"]
  external make:
    (~children: React.element, ~className: string) => React.element =
    "ButtonNext";
};

module ButtonBack_ = {
  [@react.component] [@bs.module "pure-react-carousel"]
  external make:
    (~children: React.element, ~className: string) => React.element =
    "ButtonBack";
};

module Dot_ = {
  [@react.component] [@bs.module "pure-react-carousel"]
  external make:
    (~children: React.element, ~className: string, ~slide: int) =>
    React.element =
    "Dot";
};

module Carousel = {
  [@react.component]
  let make =
      (
        ~children,
        ~className="",
        ~naturalSlideWidth,
        ~naturalSlideHeight,
        ~totalSlides,
      ) =>
    <Carousel_ className naturalSlideWidth naturalSlideHeight totalSlides>
      children
    </Carousel_>;
};

module ButtonBack = {
  [@react.component]
  let make = (~children, ~className="") =>
    <ButtonBack_ className> children </ButtonBack_>;
};

module ButtonNext = {
  [@react.component]
  let make = (~children, ~className="") =>
    <ButtonNext_ className> children </ButtonNext_>;
};

module Dot = {
  [@react.component]
  let make = (~children, ~className="", ~slide) =>
    <Dot_ className slide> children </Dot_>;
};

module Slider = {
  [@react.component] [@bs.module "pure-react-carousel"]
  external make: (~children: React.element) => React.element = "Slider";
};

module Slide = {
  [@react.component] [@bs.module "pure-react-carousel"]
  external make: (~children: React.element, ~index: int) => React.element =
    "Slide";
};

module ImageWithZoom = {
  [@react.component] [@bs.module "pure-react-carousel"]
  external make: (~src: string) => React.element = "ImageWithZoom";
};
