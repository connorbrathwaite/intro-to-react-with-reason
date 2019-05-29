type repo = {
  id: int,
  owner: string,
  title: string,
  fullName: string,
  stars: int,
  url: string,
  description: option(string),
  isFork: bool,
};

type repos = list(repo);

let parseRepoJson = json =>
  Json.Decode.{
    id: json |> field("id", int),
    owner: json |> field("owner", owner => owner |> field("login", string)),
    title: json |> field("name", string),
    fullName: json |> field("full_name", string),
    stars: json |> field("stargazers_count", int),
    url: json |> field("html_url", string),
    description: json |> optional(field("description", string)),
    isFork: json |> field("fork", bool),
  };

let parseReposResponseJson = (json): repos => Json.Decode.list(parseRepoJson, json);

let getApiUrl = (username: string) => "https://api.github.com/users/" ++ username ++ "/repos?type=all&sort=updated";

let fetchRepos = (username: string) =>
  Js.Promise.(
    username->getApiUrl
    |> Fetch.fetch
    |> then_(Fetch.Response.json)
    |> then_(json => json |> parseReposResponseJson |> (parsedRepos => Some(parsedRepos) |> resolve))
    |> catch(_err => resolve(None))
  );

module Repository = {
  [@react.component]
  let make = (~title, ~url, ~fullName, ~isFork, ~description, ~stars) => {
    <li className="flex flex-row justify-between w-full border-b">
      <div className="px-6 py-4">
        <div className="flex flex-row items-center font-mono text-base mb-2">
          <Link title href=url className="no-underline-dark mr-2"> fullName->Utils.str </Link>
          {isFork
             ? <svg className="fill-current text-green-dark h-4 w-4" viewBox="0 0 10 16">
                 <path
                   fillRule="evenodd"
                   d="M8 1a1.993 1.993 0 0 0-1 3.72V6L5 8 3 6V4.72A1.993 1.993 0 0 0 2 1a1.993 1.993 0 0 0-1 3.72V6.5l3 3v1.78A1.993 1.993 0 0 0 5 15a1.993 1.993 0 0 0 1-3.72V9.5l3-3V4.72A1.993 1.993 0 0 0 8 1zM2 4.2C1.34 4.2.8 3.65.8 3c0-.65.55-1.2 1.2-1.2.65 0 1.2.55 1.2 1.2 0 .65-.55 1.2-1.2 1.2zm3 10c-.66 0-1.2-.55-1.2-1.2 0-.65.55-1.2 1.2-1.2.65 0 1.2.55 1.2 1.2 0 .65-.55 1.2-1.2 1.2zm3-10c-.66 0-1.2-.55-1.2-1.2 0-.65.55-1.2 1.2-1.2.65 0 1.2.55 1.2 1.2 0 .65-.55 1.2-1.2 1.2z"
                 />
               </svg>
             : React.null}
        </div>
        <p className="font-mono-lighter text-xs">
          (
            switch (description) {
            | Some(desc) => desc
            | None => "No description :("
            }
          )
          ->Utils.str
        </p>
      </div>
      <div className="flex flex-row items-center px-6 py-4">
        <span className="font-mono inline-block rounded-full px-1 py-1 text-sm-dark mr-1">
          {stars->string_of_int->Utils.str}
        </span>
        <svg className="fill-current text-orange-light h-4 w-4 inline-block" viewBox="0 0 50 50">
          <path
            d="M15.2 40.6c-.2 0-.4-.1-.6-.2-.4-.3-.5-.7-.4-1.1l3.9-12-10.2-7.5c-.4-.3-.5-.7-.4-1.1s.5-.7 1-.7h12.7L25 5.9c.1-.4.5-.7 1-.7s.8.3 1 .7L30.9 18h12.7c.4 0 .8.2 1 .6s0 .9-.4 1.1L34 27.1l3.9 12c.1.4 0 .9-.4 1.1s-.8.3-1.2 0L26 33l-10.2 7.4c-.2.1-.4.2-.6.2zM26 30.7c.2 0 .4.1.6.2l8.3 6.1-3.2-9.8c-.1-.4 0-.9.4-1.1l8.3-6.1H30.1c-.4 0-.8-.3-1-.7L26 9.5l-3.2 9.8c-.1.4-.5.7-1 .7H11.5l8.3 6.1c.4.3.5.7.4 1.1L17.1 37l8.3-6.1c.2-.1.4-.2.6-.2z"
          />
        </svg>
      </div>
    </li>;
  };
};

type state =
  | NotAsked
  | Loading
  | Success(repos)
  | Failure;

type action =
  | Reset
  | LoadRepos(string)
  | LoadedRepos(repos)
  | LoadReposFailed
  | KeyDown(int);

[@react.component]
let component = (~username: string="") => {
  let (inputValue: string, setInputValue) = React.useState(() => username);

  let (state, dispatch) =
    ReactUpdate.useReducer(NotAsked, (action, state) =>
      switch (action) {
      | KeyDown(13) =>
        ReactUpdate.SideEffects(
          ({send}) => {
            (
              switch (inputValue) {
              | "" => Reset
              | nonEmptyValue when state !== Loading => nonEmptyValue->String.trim->LoadRepos
              | nonEmptyValue => nonEmptyValue->String.trim->LoadRepos
              }
            )
            ->send;
            None;
          },
        )
      | KeyDown(27) =>
        ReactUpdate.SideEffects(
          ({send}) => {
            Reset->send;
            None;
          },
        )
      | KeyDown(_) => ReactUpdate.NoUpdate
      | Reset =>
        setInputValue(_ => "");
        ReactUpdate.Update(NotAsked);
      | LoadRepos(username) =>
        ReactUpdate.UpdateWithSideEffects(
          Loading,
          ({send}) => {
            Js.Promise.(
              username->fetchRepos
              |> then_(result =>
                   (
                     switch (result) {
                     | Some(repos) when repos->List.length > 0 => repos->LoadedRepos
                     | Some(_) => LoadReposFailed
                     | None => LoadReposFailed
                     }
                   )
                   ->send
                   ->resolve
                 )
              |> ignore
            );
            None;
          },
        )
      | LoadedRepos(repos) => repos->Success->ReactUpdate.Update
      | LoadReposFailed => ReactUpdate.Update(Failure)
      }
    );
  <div className="container">
    <div className="flex flex-grow flex-col justify-start items-center">
      <input
        autoFocus=true
        className="border font-mono appearance-none py-2 px-3 w-full outline-none"
        placeholder="Enter a Github Username . . ."
        value=inputValue
        onKeyDown={e => ReactEvent.Keyboard.which(e)->KeyDown->dispatch}
        onChange={e => Utils.valueFromEvent(e)->setInputValue}
      />
      {switch (state) {
       | NotAsked => <p className="mt-8 font-mono"> "Ask Jeeves..."->Utils.str </p>
       | Failure => <p className="mt-8 font-mono"> "No results found for "->Utils.str inputValue->Utils.str </p>
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