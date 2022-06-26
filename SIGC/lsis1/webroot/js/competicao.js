function verEquipas(){
    fetch('/Organizador/getEquipas', {
        method: 'GET'
    })
        .then((res) => {
            if (res.status === 200) {
                return res.json();
            } else if (res.status === 404) {
                window.location.assign("/error404.html");
                return res.json();
            } else
                throw Error("Erro no servidor!!");
        })
        .then((data) => {
            if(data.length > 0){
                let listaEquipas = "";

                for (let i = 0; i < data.length; i++) {
                    if(data[i].organizadorLogadoAssociado === false){
                        listaEquipas += "<tr name='organizadornaoassociado'>";
                    } else {
                        listaEquipas += "<tr name='organizadorassociado'>";
                    }
                    listaEquipas += "<td class='text-center'>" + data[i].id + "</td>";
                    listaEquipas += "<td class='text-center'>" + data[i].nome + "</td>";
                    listaEquipas += "<td class='text-center'>";
                    for(let a = 0; a < data[i].competicoes.length; a++){
                        listaEquipas += " * " + data[i].competicoes[a] + "  ";
                    }
                    listaEquipas += "</td>";
                    listaEquipas += "<td class='text-center d-lg-flex justify-content-lg-end'><button class='btn btn-primary d-lg-flex justify-content-lg-center align-items-lg-center' onclick='verEquipa(" + data[i].id + ")' type='button' style='height: 25px;width: 25px;background: var(--bs-teal);margin-right: 100px;'><i class='far fa-eye d-lg-flex justify-content-lg-center align-items-lg-center'></i></button></td>";
                    listaEquipas += "</tr>";
                }

                document.getElementById("ListaEquipas").innerHTML = listaEquipas;
            }

        })
}