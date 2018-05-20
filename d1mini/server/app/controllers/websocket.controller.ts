import { Request } from 'express';
// get the parse function from the url library
import { parse as urlParse } from 'url';

// import the wsclient model from the models directory
import { WSClient } from '../models/wsclient.model';

// list of clients
let clients : WSClient[] = [];

module.exports = (ws) => {
    const app = ws.app;

    // here we can handle the inital connection from the client, 
    // this would be a good place to save clients into a clients object or something like that
    ws.getWss().on('connection', (ws) => {
        // in this starter project, we connect to the server with an id as a get parameter
        // we parse this using the url library from node-js
        const urlObj = urlParse(ws.upgradeReq.url, true);
        const id : string = urlObj.query.id.toString();

        // log id out into the console, so we can see that something connected
        console.log(`client '${id}' connected`);

        // create a new client object
        let client : WSClient = {
            id,
            instance: ws
        };
        // put it into the clients array
        clients.push(client);
    });

    /* Attach the wsHandler function to all websocket traffic on the '/websocket' endpoint    
    * you could attach an unlimmited number of handlers for differing endpoints
    * e.g.
    * /websocket/lights - for websocket clients controlling lights
    * /websocket/temperature - for temperature clients 
    * etc.     
    */
    app.ws("/websocket", wsHandler);    
}

// websocket message handler
const wsHandler = (ws, req : Request) => {

    // this is where we handle incomming messages
    ws.on('message', (msg) => {
        console.log("Message", msg);
        ws.send(msg); // echo back msg
    })
}