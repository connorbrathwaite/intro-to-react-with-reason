type categoryT =
  | SECONDARY
  | PRIMARY;

let classNameOfCategory = category =>
  "Button "
  ++ (
    switch (category) {
    | SECONDARY => "secondary"
    | PRIMARY => "primary"
    }
  );

[@react.component]
let component =
    (
      ~onClick=_ => (),
      ~title: string,
      ~children: ReasonReact.reactElement,
      ~disabled=false,
      ~category=SECONDARY,
      ~type_="button",
    ) => {
  <button onClick className={category |> classNameOfCategory} title disabled> children </button>;
};