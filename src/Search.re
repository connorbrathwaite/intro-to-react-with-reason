open Api;

type state =
  | NotAsked
  | Loading
  | Failure(option(string))
  | Success(repos);

type action =
  | Reset
  | LoadRepos(option(string))
  | LoadedRepos(option(repos))
  | LoadReposFailed(option(string))
  | KeyDown(int);

let keyCode = code =>
  switch ((code: int)) {
  | 27 =>
    Js.log("ESC");
    Reset;
  | 13 => {
    Js.log("ENTER");
    // fetchWeather(dispatch, ~searchInput=searchTerm);
  };

let reducer = (state, action) =>
  switch (action) {
  | LoadRepos(searchTerm) => Loading
  | LoadedRepos(Some(repos)) => Success(repos)
  | LoadReposFailed(Some(errorMessage)) => Failure(Some(errorMessage))
  | LoadReposFailed(None) => Failure(None)
  };

let initialState = {ui: NotAsked, searchTerm: None};

[@react.component]
let component = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let searchTerm = Belt.Option.getWithDefault(state.searchTerm, "");
  let handleOnInputChange = event =>
    event->ReactEvent.Form.target##value->String.trim->(SetSearchTerm(Some))->dispatch;
  let handleOnInputKeyDown = event => event->ReactEvent.Keyboard.which->keyCode->dispatch;

  <div className="container">
    <div className="flex flex-grow flex-col justify-start items-center">
      <input
        autoFocus=true
        className="border font-mono appearance-none py-2 px-3 w-full outline-none"
        placeholder="Enter a Github Username . . ."
        value=searchTerm
        onKeyDown=handleOnInputKeyDown
        onChange=handleOnInputChange
      />
      {switch (state) {
       | NotAsked => <p className="mt-8 font-mono"> "Ask Jeeves..."->Utils.str </p>
       | Failure(None) =>
         <p className="mt-8 font-mono"> {{"No results found for " ++ state.searchTerm ++ ":("}->Utils.str} </p>
       | Failure(Some(errorMessage)) =>
         <p className="mt-8 font-mono">
           {{"No results found for " ++ state.searchTerm ++ errorMessage ++ ":("}->Utils.str}
         </p>
       | Loading => <p className="mt-8 font-mono"> "Loading..."->Utils.str </p>
       | Success(repos) =>
         <div className="bg-white shadow rounded flex mb-8 mt-8">
           <ul className="appearance-none p-0 w-full text-grey-darker border rounded">
             {repos
              |> List.map(({id, url, description, fullName, title, stars, isFork}) =>
                   <Repository key={id->string_of_int} url description fullName isFork title stars />
                 )
              |> Array.of_list
              |> React.array}
           </ul>
         </div>
       }}
    </div>
  </div>;
};