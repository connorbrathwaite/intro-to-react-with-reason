/*
  http://reasonmlhub.com/exploring-reasonml/toc.html
 */

[@react.component]
let component = () =>
  <div className="container">
    <h1 className="text-lg"> "Crash course"->Utils.str </h1>
    <hr />
    <h2 className="font-hairline">
      <a href="http://reasonmlhub.com/exploring-reasonml/toc.html">
        "Be sure to consult this eggcellent ressource"->Utils.str
      </a>
    </h2>
    <hr />
    <h3 className="mt-4 mb-2 font-hairline"> "Functions"->Utils.str </h3>
    <hr />
    <pre> <code> "let add = (x: int, y: int) => x + y;"->Utils.str </code> </pre>
    <hr />
    <pre> <code> "let addComponents = ((x: int, y: int)) => x + y;"->Utils.str </code> </pre>
    <hr />
    <pre> <code> "let add = (~x: option(int)=?, ~y: option(int)=?, ()) => ...;"->Utils.str </code> </pre>
    <hr />
    <pre> <code> "let add = (~x: int=0, ~y: int=0, ()) => x + y;"->Utils.str </code> </pre>
    <hr />
    <h3 className="my-2 font-hairline"> "Variants & Pattern Matching"->Utils.str </h3>
    <hr />
    <pre> <code> "type color = Red | Orange | Yellow | Green | Blue | Purple;"->Utils.str </code> </pre>
    <hr />
    <pre>
      <code>
        "let stringOfColor = (c: color) => switch c {
  | Red => \"Red\"
  | Orange => \"Orange\"
  | Yellow => \"Yellow\"
  | Green => \"Green\"
  | Blue => \"Blue\"
  | Purple => \"Purple\"
};"
        ->Utils.str
      </code>
    </pre>
    <hr />
    <pre>
      <code>
        "type includeDetails = ShowEverything | HideDetails;
let stringOfContact = (~levelOfDetail: includeDetails, c: contact) => ...;
let str = stringOfContact(~levelOfDetail=ShowEverything, myContact);"
        ->Utils.str
      </code>
    </pre>
    <hr />
    <p className="my-2 font-hairline"> "Using the variant includeDetails has two advantages"->Utils.str </p>
    <ul>
      <li className="my-2 font-hairline">
        "+ It is immediately clear what \"not showing details\" means."->Utils.str
      </li>
      <li className="my-2 font-hairline"> "+ It is easy to add more modes later on."->Utils.str </li>
    </ul>
    <hr />
    <pre>
      <code>
        "type point = Point(float, float);
type shape =
  | Rectangle(point, point)
  | Circle(point, float);"
        ->Utils.str
      </code>
    </pre>
    <hr />
    <pre>
      <code>
        "let rec summarize = (l: list(int)) => switch l {
  | [] => 0
  | [head, ...tail] => head + summarize(tail)
};"
        ->Utils.str
      </code>
    </pre>
  </div>;