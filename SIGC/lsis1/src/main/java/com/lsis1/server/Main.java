package com.lsis1.server;

import io.vertx.core.Vertx;

public class Main{
    public Main(){
        Vertx vertx = Vertx.vertx();
        vertx.deployVerticle(new Server());
    }
}