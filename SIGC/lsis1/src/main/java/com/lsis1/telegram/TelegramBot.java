package telegram;

import controller.MqttController;
import io.vertx.core.Vertx;
import mqtt.MQTTCli;
import org.telegram.telegrambots.bots.TelegramLongPollingBot;
import org.telegram.telegrambots.meta.api.methods.send.SendAudio;
import org.telegram.telegrambots.meta.api.methods.send.SendMessage;
import org.telegram.telegrambots.meta.api.methods.send.SendSticker;
import org.telegram.telegrambots.meta.api.methods.send.SendVoice;
import org.telegram.telegrambots.meta.api.objects.InputFile;
import org.telegram.telegrambots.meta.api.objects.Update;
import org.telegram.telegrambots.meta.exceptions.TelegramApiException;
import keys.keys;
import javax.annotation.PostConstruct;

public class TelegramBot extends TelegramLongPollingBot {

    private final Vertx vertx;
    private final String chat_id = keys.chat_id;
    private int op = 0;

    private String subtopico = "LSIS1";

    private String subsubtopico = "teste";

    private MqttController mqttController = new MqttController();

    public TelegramBot(Vertx vertx) {
        this.vertx = vertx;
        System.out.println("(Telegram) Bot Iniciado");
        sendMessageHtml("\nπππππππππ <b>IGP</b> πππππππππ" +
                "\n" +
                "\n" +
                "\n" +
                "\n" +
                "Utilize os comandos <b>'/competicao' e '/ronda'</b> para configurar o subtΓ³pico e sub-subtΓ³pico do seu robΓ΄ π€" +
                "\n" +
                "\n" +
                "\n" +
                "\n" +
                "<b>'/comandos'</b> para ver todos os comandos disponΓ­veis" +
                "\n" +
                "\n" +
                "\n" +
                "\n" +
                "πππππππππππππππππππ");
    }

    public void sendMessage(String msg) {
        SendMessage message = new SendMessage();
        message.setText(msg);
        message.setChatId(chat_id);
        try {
            execute(message);
        } catch (TelegramApiException e) {
            e.printStackTrace(System.out);
        }
    }

    public void sendMessageHtml(String msg) {
        SendMessage message = new SendMessage();
        message.setParseMode("html");
        message.setText(msg);
        message.setChatId(chat_id);
        try {
            execute(message);
        } catch (TelegramApiException e) {
            e.printStackTrace(System.out);
        }
    }

    @Override
    public void onUpdateReceived(Update update) {

        if (update.hasMessage()) {
            System.out.print("(Telegram) Mensagem de: ");
            System.out.println(update.getMessage().getFrom().getFirstName());
            if (update.getMessage().hasText()) {
                String msgRec = update.getMessage().getText();
                System.out.println("(Telegram) " + msgRec);
                if (msgRec.contains("Boas")){
                    sendMessage("BOASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS PESSOAAAAAALLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL" +
                            "\n" +
                            "\n" +
                            "DAQUI QUEM FALA Γ O FEROMONAS E SEJAM BEM VINDOS A MAISSSSSSSSSSSSSSS UM VIDEO" +
                            "\n" +
                            "\n" +
                            "ππππππππππππππππ");
                    try {
                        sendVoice("https://cdn.discordapp.com/attachments/895411302263050274/987854457675075644/Nova-Intro-do-Feromonas.opus");
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }else if (msgRec.contains("/competicao")) {
                    sendMessage("Insira o nome da competiΓ§Γ£o");
                    op = 1;
                } else if (msgRec.contains("/ronda")) {
                    sendMessage("Insira o numero da ronda");
                    op = 2;
                } else if (msgRec.contains("/vertopico")) {
                    vertopico();
                    op = 0;
                }else if (msgRec.contains("/comandos")) {
                    vercomandos();
                    op = 0;
                }else{
                    ops(msgRec);
                }
            }
        }
    }

    private void sendVoice(String s) throws TelegramApiException {
        SendVoice sendVoice = new SendVoice();
        InputFile file = new InputFile(s);
        sendVoice.setVoice(file);
        sendVoice.setChatId(chat_id);
        sendVoice.setDuration(13);
        execute(sendVoice);
    }

    private void vercomandos() {
        sendMessage("\nLista de comandos disponiveis\n\n" +
                "'/competicao' - Insira o nome da competiΓ§Γ£o a que pertence (subtΓ³pico)\n" +
                "'/ronda' - Insira o nΓΊmero da ronda que esta a competir (sub-subtΓ³pico)\n" +
                "'/vertopico' - Mostra o tΓ³pico em que esta inscrito no mqtt\n" +
                "'/comandos' - Mostra todos os comandos disponΓ­veis");
    }

    private void vertopico() {
        sendMessage("EstΓ‘ a decorrer a competiΓ§Γ£o:" + subtopico + " ronda:" + subsubtopico +
                "\n" +
                "\n" +
                "Para alterar porfavor utilize '/competicao' e '/ronda'");
    }

    @Override
    public String getBotUsername() {
        return "@lsis1equipa6bot";
    }

    @Override
    public String getBotToken() {
        return keys.Apikey;
    }

    public void ops(String msgRec){
        switch (op){
            case 1:
                String subtopicotemp = subtopico;
                subtopico = msgRec;
                mqttController.setSubtopico(subtopico);
                sendMessageHtml("(Sub-TΓ³pico) Competicao alterada de <s>" + subtopicotemp + "</s> para: " + subtopico);
                System.out.println("(telegram)[Sub-TΓ³pico] Competicao alterada para: " + subtopico);
                vertopico();
                op = 0;
                break;
            case 2:
                String subsubtopicotemp = subsubtopico;
                subsubtopico = msgRec;
                mqttController.setSubsubtopico(subsubtopico);
                sendMessageHtml("(Sub-Sub-TΓ³pico) Ronda alterada de <s>" + subsubtopicotemp + "</s> para: " + subsubtopico);
                System.out.println("(telegram)[Sub-Sub-TΓ³pico] Ronda alterada para: " + subsubtopico);
                vertopico();
                op = 0;
                break;
            default:
                break;
        }
    }

    public String getChat_id() {
        return chat_id;
    }

    public int getOp() {
        return op;
    }

    public void setOp(int op) {
        this.op = op;
    }

    public String getSubtopico() {
        return subtopico;
    }

    public void setSubtopico(String subtopico) {
        this.subtopico = subtopico;
    }

    public String getSubsubtopico() {
        return subsubtopico;
    }

    public void setSubsubtopico(String subsubtopico) {
        this.subsubtopico = subsubtopico;
    }
}