import * as express from 'express';
import * as ws from 'express-ws';
import * as bodyParser from 'body-parser';
import * as morgan from 'morgan';
import * as ebs from 'express-handlebars';
import * as path from 'path';


// import controllers
import { WelcomeController} from './controllers'; // import the controllers we need from the './controllers' folder

export const app : express.Application = express();
const port: number = parseInt(process.env.PORT) || 3000; // if port is set in env (e.g. export PORT = 3000) use the env var, else use 3000

// setup websockets
const expressWS : ws.Instance = ws(app);

// setup libraries; bodyParser (for parsing parameters in express) and Morgan (for logging purposes)
// handlebars for generating html

app.use(morgan('dev'));
app.use(bodyParser.json());

//setup handlebars aswell as layouts dir
// this assumes that you are running from the "server" directory and not "app"
// e.g. using npm run
app.set('views', path.resolve(__dirname, "views"));
app.engine('handlebars', ebs({
    defaultLayout: 'main',        
    layoutsDir: path.resolve(__dirname, "views/layouts")}));
app.set('view engine', 'handlebars');


// strap the controllers on to the webapp
app.use("/welcome", WelcomeController);


// include the websockets controller, this is where alot of magic happens :) 
const wss = require('./controllers/websocket.controller')(expressWS);

// set the application to listen on the specified port
app.listen(port, () => {
    console.log(`Server is up, listening on port: ${port}`); 
});