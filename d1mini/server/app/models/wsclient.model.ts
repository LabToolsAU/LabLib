import * as ws from 'express-ws';
export type WSClient = {
    id: string,
    instance: ws.Instance
}