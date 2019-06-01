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

let parseReposResponseJson = (repos: Js.Json.t) => repos |> Json.Decode.list(parseRepoJson);

let getApiUrl = username => "https://api.github.com/users/" ++ username ++ "/repos?type=all&sort=updated";

let fetchRepos = (~searchInput) =>
  searchInput
  |> getApiUrl
  |> Fetch.fetch
  |> Js.Promise.then_(Fetch.Response.json)
  |> Js.Promise.then_(json => json |> parseReposResponseJson |> Js.Promise.resolve);