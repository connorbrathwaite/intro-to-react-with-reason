[@react.component]
let component =
    (~src: string, ~alt: string, ~text: string, ~subText: string, ~ctas: list(string), ~onClick, ~isInCart=false) =>
  <div className="flex flex-auto flex-col border border-black">
    <img src alt />
    <div className="flex flex-auto flex-col p-2">
      <p className="font-bold mb-2"> text->Utils.str </p>
      <p className="text-gray-700"> subText->Utils.str </p>
      <button className="text-gray-700" onClick> "Add to Cart"->Utils.str </button>
    </div>
    <div className="flex flex-auto flex-row flex-wrap p-2">
      {ctas
       |> List.map(cta => <a key=cta className="inline-block m-1 text-sm font-semibold"> cta->Utils.str </a>)
       |> Array.of_list
       |> React.array}
    </div>
  </div>;