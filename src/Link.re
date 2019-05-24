[@react.component]
let make = (~className, ~href: string, ~title="", ~children) => {
  let handleClick = (href, event) =>
    if (!ReactEvent.Mouse.defaultPrevented(event)) {
      ReactEvent.Mouse.preventDefault(event);
      ReasonReact.Router.push(href);
    };

  <a className href rel="noopener noreferrer" target="_blank" title onClick={handleClick(href)}> children </a>;
};