[@react.component]
let make = (~width: option(string)=?, ~height: option(string)=?) =>
  <div style={ReactDOMRe.Style.make(~width?, ~height?, ())} />;