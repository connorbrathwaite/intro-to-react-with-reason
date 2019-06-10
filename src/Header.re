[@react.component]
let component = () =>
  <header className="flex flex-grow flex-wrap items-center m-4">
    <Link title="Intro" href="/intro" className="hover:text-gray-500 text-xs uppercase mr-4">
      "Intro"->Utils.str
    </Link>
    <Link title="Cards" href="/cards" className="hover:text-gray-500 text-xs uppercase mr-4">
      "Cards"->Utils.str
    </Link>
    <Link title="Async Hooks" href="/search" className="hover:text-gray-500 text-xs uppercase mr-4">
      "Async Hooks"->Utils.str
    </Link>
    <Link title="Vanilla React" href="/vanilla-react" className="hover:text-gray-500 text-xs uppercase mr-4">
      "Vanilla React Interop"->Utils.str
    </Link>
  </header>;
