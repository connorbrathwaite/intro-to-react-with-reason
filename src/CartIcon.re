[@react.component]
let make = (~count=0) =>
  <div className="sticky flex align-center justify-end m-4"> {count->string_of_int->Utils.str} </div>;
