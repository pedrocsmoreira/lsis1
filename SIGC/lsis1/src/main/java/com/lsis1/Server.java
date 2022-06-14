package com.lsis1;

import io.vertx.core.AbstractVerticle;
import io.vertx.ext.web.Router;
import io.vertx.core.Promise;
import io.vertx.core.http.HttpMethod;
import io.vertx.core.http.HttpServerOptions;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.StaticHandler;
import static io.vertx.ext.web.handler.StaticHandler.DEFAULT_WEB_ROOT;
import com.lsis1.Class.MQTT;
import com.lsis1.Class.Repository;

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
        // serve index
        router.route("/").handler(StaticHandler.create(webRoot));


        router.route(HttpMethod.GET, "/alunosJson").handler(handlers::sendStringJson);
        router.route(HttpMethod.GET, "/alunosString").handler(handlers::sendArrayAsString);
        router.route(HttpMethod.GET, "/paginaNova")
                .handler(handlers::paginaNova);//ou StaticHandler.create(webRoot + "/html/nova1.html"));
        router.route(HttpMethod.GET, "/paginaNova2")
                .handler(handlers::paginaNova2);//ou StaticHandler.create(webRoot + "/html/nova1.html"));

        
        // ATENÇÃO: necessário usar "bodyHandler" quando se pretende ler o body do pedido
        //  - nos POST seguintes o body contém os dados do aluno
        router.route("/alunos/*").handler(BodyHandler.create());
        // criarALuno() e actualizarALuno() estão na classe Handlers
        router.route(HttpMethod.POST, "/alunos").handler(handlers::criarAluno);
        router.route(HttpMethod.PUT, "/alunos/:numAluno").handler(handlers::actualizarAluno);

        return router;
    }

}