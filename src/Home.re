[@react.component]
let component = () =>
  <div className="grid m-4">
    <Card.component
      src="https://tailwindcss.com/img/card-top.jpg"
      alt="Lorem"
      text="Lorem"
      subText="Foo Bar"
      ctas=["First", "Second"]
    />
    <Card.component
      src="https://tailwindcss.com/img/card-top.jpg"
      alt="Ipsum"
      text="Ipsum"
      subText="Chicken Wing"
      ctas=["Just", "Sauce"]
    />
    <Card.component
      src="https://tailwindcss.com/img/card-top.jpg"
      alt="Roman Word"
      text="Roman Word"
      subText="Pleb"
      ctas=["Three", "Four", "Five"]
    />
  </div>;