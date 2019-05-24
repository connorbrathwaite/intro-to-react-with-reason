const ReactDOM = require("react-dom");
const React = require("react");

const TYPES = {
  success: "green",
  info: "indigo",
  error: "red"
};

const Alert = function({ isVisible = true, message, type = TYPES.info }) {
  const color = TYPES[type];
  const [_isVisible, _setIsVisble] = React.useState(isVisible);

  if (!_isVisible) {
    return null;
  }

  const renderBadge =
    type === TYPES.success
      ? React.createElement(
          "span",
          {
            className: `flex bg-${color}-700 px-2 py-1 mr-3 text-xs font-bold uppercase`
          },
          "Yay"
        )
      : null;

  const renderMessage = React.createElement(
    "span",
    {
      className: "flex-auto text-left mr-2"
    },
    message
  );

  const renderClose = React.createElement(
    "span",
    {
      className: "fill-current opacity-75 h-4 w-4",
      onClick: () => _setIsVisble(false)
    },
    "x"
  );

  return React.createElement(
    "div",
    {
      className: `flex w-auto bg-${color}-800 items-center text-${color}-100 font-hairline leading-none p-2`,
      role: "alert"
    },
    renderBadge,
    renderMessage,
    renderClose
  );
};

module.exports = Alert;
