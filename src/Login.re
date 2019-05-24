[@bs.val] external alert: string => unit = "alert";

let loginUrl = "some/url";

type loginError =
  | EMAIL_NOT_FOUND
  | INVALID_PASSWORD
  | OTHER;

let stringToLoginError = str =>
  switch (str) {
  | "EMAIL_NOT_FOUND" => Some(EMAIL_NOT_FOUND)
  | "INVALID_PASSWORD" => Some(INVALID_PASSWORD)
  | _ => Some(OTHER)
  };

[@react.component]
let component = () => {
  let (email, setEmail) = React.useState(() => "");
  let (password, setPassword) = React.useState(() => "");
  let (error, setError) = React.useState(() => None);

  let handleEmailChange = e => ReactEvent.Form.target(e)##value |> setEmail;
  let handlePasswordChange = e => ReactEvent.Form.target(e)##value |> setPassword;

  let handlePromiseFailure =
    [@bs.open]
    (
      fun
      | Request.PostError(err) => {
          err;
        }
    );

  let handleFormSubmit = e => {
    ReactEvent.Form.preventDefault(e);
    let payload = Js.Dict.empty();
    Js.Dict.set(payload, "email", Js.Json.string(email));
    Js.Dict.set(payload, "password", Js.Json.string(password));
    Js.Promise.(
      Request.post(loginUrl, payload)
      |> then_(res =>
           {
             alert("Login successful!");
             setError(_ => None);
           }
           |> resolve
         )
      |> catch(e =>
           (
             switch (handlePromiseFailure(e)) {
             | Some(err) => setError(_ => stringToLoginError(err))
             | None => setError(_ => None)
             }
           )
           |> resolve
         )
      |> ignore
    );
  };

  <div className="Login">
    <h2> "Login"->React.string </h2>
    <form onSubmit=handleFormSubmit>
      <div className="inputField">
        <input type_="email" placeholder="Email" value=email onChange=handleEmailChange required=true />
        {switch (error) {
         | Some(EMAIL_NOT_FOUND) => <div className="error"> "Email not found"->React.string </div>
         | _ => React.null
         }}
      </div>
      <div className="inputField">
        <input type_="password" placeholder="Password" value=password onChange=handlePasswordChange required=true />
        {switch (error) {
         | Some(INVALID_PASSWORD) => <div className="error"> "Invalid password"->React.string </div>
         | _ => React.null
         }}
      </div>
      <Button.component title="Login" category=Button.PRIMARY> "Login"->React.string </Button.component>
    </form>
  </div>;
};