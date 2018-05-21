import * as ws from 'express-ws';
export type WSClient = {
    id: string,
    ws: any
}