package com.lsis1;

import io.vertx.core.AbstractVerticle;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.core.Promise;
import io.vertx.core.http.HttpMethod;
import io.vertx.core.http.HttpServerOptions;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.StaticHandler;
import static io.vertx.ext.web.handler.StaticHandler.DEFAULT_WEB_ROOT;

import com.lsis1.Model.Competicao;
import com.lsis1.Model.MQTT;
import com.lsis1.Model.Repository;
import com.lsis1.Controller.compController;

/*
 * 
 * @author G10
 */


public class Server extends AbstractVerticle{
    String webRoot = DEFAULT_WEB_ROOT;
    Router router;
    MQTT mqtt;

    @Override
    public void start(Promise<Void> startPromise) throws Exception {
              
        Repository repo = new Repository();
        Handlers handlers = new Handlers(repo);
        router = routes(handlers);
        
        mqtt = new MQTT(vertx, repo);
        
        HttpServerOptions options = new HttpServerOptions();
        options.setHost("127.0.0.1").setPort(8004);

        vertx.createHttpServer(options)
            .requestHandler(router) //usa o router para manipular qualquer pedido
            .listen(res -> {
                  if (res.succeeded()) {               
                      startPromise.complete();
                      System.out.println("Servidor HTTP no porto " + options.getPort());
                  } else {               
                      startPromise.fail(res.cause());
                      System.out.println("Nao foi possivel iniciar o servidor HTTP");
                  }
          });
    }

    private Router routes(Handlers handlers) {
        router = Router.router(vertx);

        router.route().handler(StaticHandler.create().setWebRoot(webRoot));
        router.route("/").handler(StaticHandler.create(webRoot));

        router.route("/login").handler(BodyHandler.create());
        router.route(HttpMethod.POST, "/criarComp").handler(handlers::criarCompeticao);
        router.route(HttpMethod.POST, "/loginComp").handler(handlers::loginCompeticao);
        router.route(HttpMethod.POST, "/addRonda").handler(handlers::adicionarDados);

        return router;
    }
}