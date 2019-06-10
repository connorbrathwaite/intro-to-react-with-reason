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
    <h3 className="mt-4 mb-2 font-hairline"> "Functions and their signatures"->Utils.str </h3>
    <hr />
    <pre> <code> "let add = (x: int, y: int) => x + y;"->Utils.str </code> </pre>
    <hr />
    <p className="my-2 font-hairline">
      "Labeled arugments with defined types, \"optional\" values, note: partial application"->Utils.str
    </p>
    <pre> <code> "let add = (~x: option(int)=?, ~y: option(int)=?, ()) => ...;"->Utils.str </code> </pre>
    <hr />
    <p className="my-2 font-hairline"> "Labeled arugments with defined types and default values"->Utils.str </p>
    <pre> <code> "let add = (~x: int=0, ~y: int=0, ()) => x + y;"->Utils.str </code> </pre>
    <hr />
    <p className="my-2 font-hairline"> "Recurision"->Utils.str </p>
    <pre>
      <code>
        "let rec summarize = (l: list(int)) => switch l {
  | [] => 0
  | [head, ...tail] => head + summarize(tail)
};"
        ->Utils.str
      </code>
    </pre>
    <p className="my-2 font-hairline"> "Reverse-application or pipe operator"->Utils.str </p>
    <pre> <code> "|>"->Utils.str </code> </pre>
    <p className="my-2 font-hairline">
      "The operator |> is called reverse-application operator or pipe operator. It lets you chain function calls: x |> f is the same as f(x). That may not look like much, but it is quite useful when combining function calls."
      ->Utils.str
    </p>
    <pre>
      <code>
        "[4, 2, 1, 3, 5]
|> List.map(x => x + 1)
|> List.filter(x => x < 5)
|> List.sort(compare);"->Utils.str
      </code>
    </pre>
    <hr />
    <a className="my-2 font-hairline" href="https://bucklescript.github.io/docs/en/pipe-first">
      "BuckleScript has a special |. (or -> for Reason) pipe syntax for dealing with various situations. This operator has many uses."
      ->Utils.str
    </a>
    <pre> <code> "a
->foo(b)
->bar;

// is equal to

bar(foo(a, b));"->Utils.str </code> </pre>
    <hr />
    <h3 className="my-2 font-hairline"> "Variants & Pattern Matching"->Utils.str </h3>
    <hr />
    <pre> <code> "type color = Red | Orange | Yellow | Green | Blue | Purple;"->Utils.str </code> </pre>
    <hr />
    <p className="my-2 font-hairline"> "Lookup table, similar to JS"->Utils.str </p>
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
    <a className="my-2 font-hairline" href="http://reasonmlhub.com/exploring-reasonml/ch_records.html">
      "Could also return records i.e {x: 12, y: -2};"->Utils.str
    </a>
    <hr />
    <p className="my-2 font-hairline"> "Prefer variants over booleans since:"->Utils.str </p>
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
    <p className="my-2 font-hairline"> "Composing types"->Utils.str </p>
    <pre>
      <code>
        "type point = Point(float, float);

type shape =
  | Rectangle(point, point)
  | Circle(point, float);"
        ->Utils.str
      </code>
    </pre>
  </div>;
