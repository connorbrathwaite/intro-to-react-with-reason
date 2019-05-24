// https://reasonml.github.io/docs/en/module

let str = React.string;

let valueFromEvent = event => event->ReactEvent.Form.target##value;