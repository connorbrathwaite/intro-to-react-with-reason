[@react.component]
let component =
    (
      ~src: string,
      ~alt: string,
      ~title: string,
      ~subText: string,
      ~price: int,
      ~ctas: list(string),
      ~handleOnClick,
      ~isInCart: bool,
    ) => {
  <div className="flex flex-auto flex-col border border-black">
    <img src alt />
    <div className="flex flex-auto flex-col p-2">
      <p className="font-bold mb-2"> title->Utils.str </p>
      <p className="font-semibold"> subText->Utils.str </p>
      <p className="font-bold"> {price->string_of_int->Utils.str} </p>
      <button className="text-gray-700" onClick=handleOnClick>
        (isInCart ? "Remove from Cart" : "Add to Cart")->Utils.str
      </button>
    </div>
    <div className="flex flex-auto flex-row flex-wrap p-2">
      {ctas
       |> List.map(cta => <a key=cta className="inline-block m-1 text-sm font-semibold"> cta->Utils.str </a>)
       |> Array.of_list
       |> React.array}
    </div>
  </div>;
};