function criar(){
    return fetch("/criarComp").then((res) => {
        return res.json();
    }).then((result) => {
        console.log("CRIAR NOVA COMPETIÇÃO");
    }).catch(erro => {
        console.log(erro);
    });
}