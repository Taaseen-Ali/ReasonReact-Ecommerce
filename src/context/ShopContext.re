open ShopifyBuy;
module Actions = {
  type actions =
    | ToggleCart(bool)
    | UpdateCart;
};
open Actions;

let client =
  shopifyBuy->buildClient({
    storefrontAccessToken: "dd4d4dc146542ba7763305d71d1b3d38",
    domain: "graphql.myshopify.com",
  });

type shopContext = (
  ShopifyBuy.Types_.client,
  array(ShopifyBuy.Types_.lineItem),
  option(string),
  actions => unit,
);

let initialContext: shopContext = (client, [||], None, _ => ignore());

let context = React.createContext(initialContext);
let useShop = () => React.useContext(context);
