[@react.component]
let make = (~children) => {
  <>
    <pre className="mb-2">
      <code>
        "[@react.component] [@bs.module]
external make: (~isVisible: bool=?, ~_type: string=?, ~message: string) => React.element = \"./Alert\";"
        ->Utils.str
      </code>
    </pre>
    children
  </>;
};
