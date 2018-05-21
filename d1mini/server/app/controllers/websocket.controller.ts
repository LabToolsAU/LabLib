import { parse as urlParse } from 'url';
import { WSClient } from '../models';
import { Response, Request } from 'express';

let clients: WSClient[] = [];

module.exports = (ews) => {
    const app = ews.app;
    ews.getWss().on('connection', (ws) => {
        const urlObj = urlParse(ws.upgradeReq.url, true);        
        const id = urlObj.query.id.toString();                

        let client : WSClient = {
            id,
            ws
        }
        clients.push(client); // save client in our clients array
        console.log(`${id} connected`);
    });
    app.ws('/websockets', wsHandler);    
}


/*
* The sendMessage function is exported so it can be imported to any module
* in the app, and can be used to send messages to a specific client
* or to mass send (here we could also have used the server broadcast function)
* The main difference between sending to all clients like this and to use the broadcast
* function is that we can actually control what clients are listed in the 'clients' array
* as opposed to just broadcasting out to all connections
* Usage: sendMessage(message, clientID (optional) ); - if no clientID is provided we send to
* all clients.
*/
export const sendMessage = (message:string, clientID:string = null) => {
    if(clientID){
        var c = clients.find((e) => {
            return e.id == clientID;
        })
        c.ws.send(message);
    } else {
        clients.forEach(c => {
            c.ws.send(message);
        })
    }
}

/* 
* Get the list of clients associated with the sockets controller
*/
export const getClients = ():WSClient[] => {
    return clients;
}

const wsHandler = (ws, req) => {

    ws.on('message', function(msg) {                
        const urlObj = urlParse(ws.upgradeReq.url, true);       
        const btnID = urlObj.query.id;
        console.log(btnID,"clicked to answer");        
    });
}