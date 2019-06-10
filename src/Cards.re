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
              alt="Lorem"
              ctas=["First", "Second"]
              handleOnClick={_ => onClick(id)}
              isInCart={isInCart(id)}
              key={id->string_of_int}
              price
              src
              title
              subText="Foo Bar"
            />
          )
       |> Array.of_list
       |> React.array}
    </div>
  </>;
};
