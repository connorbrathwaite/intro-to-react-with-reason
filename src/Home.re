module CartIcon = {
  [@react.component]
  let make = (~count=0) =>
    <div className="sticky flex align-center justify-end m-4"> {count->string_of_int->Utils.str} </div>;
};

type product = {
  id: int,
  title: string,
  src: string,
  price: int,
};

type products = list(product);

type state = {
  products,
  cart: list(option(int)),
  isCheckingOut: bool,
};

type action =
  | CartAdd(option(int))
  | CartSubtract(option(int))
  | CartCheckout;

type isInCart = bool;

let rec getListLength = (myList: list('a)) =>
  switch (myList) {
  | [] => 0
  | [_, ...tail] => 1 + getListLength(tail)
  };

let findProductIdInCart = (cart: list(int), productId: int) =>
  switch (cart |> List.find(cartProductId => productId == cartProductId)) {
  | None => false
  | Some(productId) =>
    Js.log(productId);
    true;
  };

[@react.component]
let component = () => {
  let initialState = {
    cart: [],
    products: [{id: 1, title: "Stessy", src: "https://tailwindcss.com/img/card-top.jpg", price: 2}],
    isCheckingOut: false,
  };

  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | CartAdd(Some(productId)) => {...state, cart: [Some(productId), ...state.cart]}
        | CartSubtract(productId) => {
            ...state,
            cart: state.cart |> List.filter(cartProductId => cartProductId != productId),
          }
        | CartCheckout => {...state, isCheckingOut: true}
        },
      initialState,
    );

  <>
    <CartIcon count={state.cart |> List.length} />
    <div className="product-grid m-4">
      <Card.component
        alt="Lorem"
        ctas=["First", "Second"]
        src="https://tailwindcss.com/img/card-top.jpg"
        subText="Foo Bar"
        text="Lorem"
        isInCart=true
        onClick={e => findProductIdInCart(state.cart, 1) ? dispatch(CartAdd(1)) : dispatch(CartSubtract(1))}
      />
    </div>
  </>;
};