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
  cart: list(int),
  isCheckingOut: bool,
};

type action =
  | CartAdd(int)
  | CartSubtract(int)
  | CartCheckout;

let rec getListLength = (myList: list('a)) =>
  switch (myList) {
  | [] => 0
  | [_, ...tail] => 1 + getListLength(tail)
  };

[@react.component]
let component = () => {
  let initialState = {
    cart: [],
    products: [
      {id: 1, title: "Stessy", src: "https://tailwindcss.com/img/card-top.jpg", price: 2},
      {id: 2, title: "Messy", src: "https://tailwindcss.com/img/card-top.jpg", price: 3},
    ],
    isCheckingOut: false,
  };

  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | CartAdd(productId) => {...state, cart: List.append([productId], state.cart)}
        | CartSubtract(productId) => {
            ...state,
            cart: List.filter(cartProductId => cartProductId !== productId, state.cart),
          }
        | CartCheckout => {...state, isCheckingOut: true}
        },
      initialState,
    );

  let isInCart = productId => List.exists(cartProductId => productId === cartProductId, state.cart);

  let onClick = productId =>
    isInCart(productId) ? dispatch(CartSubtract(productId)) : dispatch(CartAdd(productId));

  Js.log(state.cart |> Array.of_list);

  <>
    <CartIcon count={state.cart |> List.length} />
    <div className="product-grid m-4">
      {state.products
       |> List.map(({id, title, src, price}) =>
            <Card.component
              key={id->string_of_int}
              alt="Lorem"
              price
              title
              ctas=["First", "Second"]
              src
              subText="Foo Bar"
              isInCart={isInCart(id)}
              handleOnClick={_ => onClick(id)}
            />
          )
       |> Array.of_list
       |> React.array}
    </div>
  </>;
};