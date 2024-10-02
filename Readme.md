O programa de Mercado foi desenvolvido com funcionalidades para cadastrar produtos, listar os produtos disponíveis, adicionar itens ao carrinho, visualizar o carrinho e concluir a compra. O programa foi dividido em várias funções para modularizar cada operação.Principais partes do programa:

### Estruturas Usadas:
1. **Produto**: Representa cada produto disponível para compra, armazenando o ID, nome e preço.
2. **Carrinho**: Armazena o ID do produto e a quantidade desse produto que foi adicionada ao carrinho.

### Funcionalidades:

1. **Cadastrar Produto**:
   - Ao cadastrar um produto, o usuário deve fornecer um ID único, um nome válido (composto apenas por letras), e o preço. O programa verifica se o produto já foi cadastrado, seja pelo nome ou pelo ID, para evitar que produtos sejam duplicados.

2. **Listar Produtos**:
   - A lista de produtos cadastrados é exibida ao usuário. Durante a listagem, adicionei a possibilidade de modificar as informações dos produtos diretamente após visualizá-los, como alterar o nome, o preço ou remover o produto.

3. **Comprar Produtos**:
   - O usuário pode adicionar produtos ao carrinho de compras informando o ID e a quantidade desejada. O carrinho armazena cada item, somando quantidades caso o mesmo produto seja adicionado mais de uma vez.

4. **Visualizar Carrinho**:
   - Ao visualizar o carrinho, são exibidos os produtos adicionados, junto com o nome, ID, preço unitário e quantidade. Além disso, dentro dessa funcionalidade, adicionei a possibilidade de alterar a quantidade de um produto ou removê-lo do carrinho diretamente.

5. **Concluir Compra**:
   - Após verificar os itens do carrinho, o usuário pode fechar a compra. O programa calcula o valor total da compra e esvazia o carrinho após o pedido ser concluído. As opçoes ainda aparecem podendo cadastrar novos produtos, fazer compras novamente ou finalmente terminar o programa reiniciando-o, como descrito a seguir.

6. **Função de Reinício (restart)**:
   - Implementei a função `restart`, que limpa todo o programa, todo os produtos cadastrados anteriormente são apagados e caso o carrinho esteja com algum produto ele apaga também e volta ao inicio, para reiniciar todo o processo se quiser.

### Integração com o Menu:
O menu principal foi feito para que o usuário possa escolher entre algumas opçoes, como cadastrar produtos, visualizar o carrinho, concluir a compra ou reiniciar o programa. As operações de modificação do carrinho e dos produtos estão integradas nas próprias funções de visualização, sem a necessidade de voltar ao menu principal para realizar essas alterações.

### Opçoes:
Todas as opçoes do menu são aparecidas juntas, porém é necessário primeiro Cadastrar algum produto, para assim poder Compra-lo e aparecer no Carrinho, e por fim Finalizar o pedido. Caso essa ordem não seja obedecida, o usuario sera informado e convidado a digitar a opçao correta.

### Compilar e Executar:

1. Salve o código com o nome `mercado.c`.
2. Certifique-se de ter um compilador C instalado, como o **GCC**.
3. Abra o terminal ou o prompt de comando e navegue até a pasta onde o arquivo está salvo.
4. Compile o código com o comando `gcc mercado.c -o mercado`. Isso gera um arquivo executável chamado `mercado`.
5. Para executar o programa, use:
   - No Windows: `mercado.exe`
   - No Linux/macOS: `./mercado`

Se estiver no Linux ou macOS, troque `system("cls")` por `system("clear")` para limpar a tela corretamente.