・操作方法
矢印キー→矢印の方向に移動(止まらない)
SPACEキー→目的地の表示

・ゲームについて
SPACEキーを押したら目的地をが設定してある敵の進む道が見れます。
ゲーム性はなく敵AIだけ作りました。
AI関連については「AIについて.txt」参照

・AI以外で頑張ったところ等
罠はリストでxの位置が小さい順番になるように管理(xと同じならyが小さくなる)(同じ位置の場合はリストに入れず素通りする)
敵は思考以外の動きはすべて同じなのでEnemyクラスを継承して作成(ただプレイヤーも同じ動きのためCharacterクラスを作成して継承するのがよかったかもしれない)。

・バグとか
複数の敵が目的地に向かって進んでいる場合SPACEキーを押しても一体しか反応しない(目的地までの道を表示する際に全て戻しているため)
目的地までの進む道に罠がある場合罠が見えなくなる(目的地を表示する道を普通の地面に変更するため)(罠自体は機能する)