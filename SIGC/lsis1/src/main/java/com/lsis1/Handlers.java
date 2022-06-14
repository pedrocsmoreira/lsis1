package com.lsis1;

import com.lsis1.Class.Repository;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.Json;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.RoutingContext;
import static io.vertx.ext.web.handler.StaticHandler.DEFAULT_WEB_ROOT;
import java.util.logging.Logger;

/*
 * 
 * @author Grupo10
 */

public class Handlers {
    String webRoot = DEFAULT_WEB_ROOT;

    Repository repo;
    public Handlers(Repository repo) {
        this.repo = repo;
    }
    
}