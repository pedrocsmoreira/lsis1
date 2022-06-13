package com.lsis1;

import io.vertx.core.Vertx;

public class Main{
    Vertx vertx = Vertx.vertx();
    vertx.deployVerticle(new Server());
}