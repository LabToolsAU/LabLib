import * as express from 'express';
import * as ws from 'express-ws';

// import controllers
import { WelcomeController} from './controllers'; // import the controllers we need from the './controllers' folder

export const app : express.Application = express();
const port: number = parseInt(process.env.PORT) || 3000; // if port is set in env (e.g. export PORT = 3000) use the env var, else use 3000

const expressWS : ws.Instance = ws(app);

app.use("/welcome", WelcomeController);

// include the websockets controller, this is where alot of magic happens :) 
const wss = require('./controllers/websocket.controller')(expressWS);

// set the application to listen on the specified port
app.listen(port, () => {
    console.log(`Server is up, listening on port: ${port}`); 
});