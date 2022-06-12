package com.lsis1;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Promise;

public class Server extends AbstractVerticle{

    @Override
    public void start(Promise<Void> startPromise) throws Exception {
        vertx.createHttpServer().requestHandler(req -> { req.response()
        .putHeader("content-type", "text/plain")
        .end("Olá do servidor HTTP Vert.x!"); }).listen(8888, http -> {
            if(http.succeeded()) {
                startPromise.complete();
                System.out.println("Servidor HTTP iniciou na port 8888");
            }else {
                System.out.println("Servidor HTTP erro! " + http.cause());
                startPromise.fail(http.cause());
            }
        });
    }

}