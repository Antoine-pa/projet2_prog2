#import "@preview/touying:0.7.3": *
#import themes.university: *
#import "@preview/diagraph:0.3.3": raw-render

#show: university-theme.with(
  aspect-ratio: "16-9",
  config-info(
    title: [PixelWar],
    subtitle: [Projet final: Génie logiciel],
    author: [Aurélien, Pascal, Hadrien],
    institution: [ENS Rennes],
  ),
)

#title-slide()

== Plan

#components.adaptive-columns(
  outline(title: none, indent: 1em)
)

= Architecture

== Diagramme de classes

#align(center)[
  #raw-render(
    ```dot
    digraph {
      rankdir=BT
      graph [size="10,5.5" ratio=compress ranksep=0.9 nodesep=0.5]
      node [shape=box fontsize=13 style=filled fillcolor="#FAFAFA" color="#888888"]
      edge [color="#444444"]

      { rank=same Socket Message }
      { rank=same ClientSocket ServeurSocket Request }
      { rank=same Client Serveur ImageEditor DispMgr Displayer }

      Socket        [label="Socket\n_fd, _port, _addr"]
      ClientSocket  [label="ClientSocket\n_ip"]
      ServeurSocket [label="ServeurSocket\n_client_fd"]
      Message       [label="Message\n_content, _type"]
      Request       [label="Request\n_x, _y, _r, _g, _b"]
      Client        [label="Client"]
      Serveur       [label="Serveur\n_width, _height"]
      ImageEditor   [label="ImageEditor\nsf::Image, mutex"]
      DispMgr       [label="DisplayerManager\n_displayer_fds"]
      Displayer     [label="Displayer\n_buf"]

      ClientSocket -> Socket        [arrowhead=empty]
      ServeurSocket -> Socket       [arrowhead=empty]
      Request      -> Message       [arrowhead=empty]

      Client    -> ClientSocket  [arrowhead=open style=dashed]
      Serveur   -> ServeurSocket [arrowhead=open style=dashed]
      DispMgr   -> ServeurSocket [arrowhead=open style=dashed]
      Displayer -> ClientSocket  [arrowhead=open style=dashed]
    }
    ```
  )
]

== Binaires & fichiers sources

#table(
  columns: (auto, 1fr),
  stroke: 0.5pt,
  inset: 7pt,
  fill: (_, row) => if row == 0 { luma(215) },
  [*Binaire*], [*Fichiers source*],
  [`server`],            [`main_serveur`, `serveur`, `displayer_manager`, _COMMON_],
  [`client`],            [`main_client`, `client`, _COMMON_],
  [`displayer`],         [`main_displayer`, `displayer`, _COMMON_],
  [`pxlwar_client_test`],[`main_client_test`, `client`, `displayer`, _COMMON_],
)

#v(0.4em)
#text(size: 0.85em)[_COMMON : `socket`, `client_socket`, `serveur_socket`, `message`, `image_editor`_]

= Protocole & implémentation

== Protocole réseau

#table(
  columns: (auto, 1fr, 1fr),
  stroke: 0.5pt,
  inset: 7pt,
  fill: (_, row) => if row == 0 { luma(215) },
  [*Émetteur*],  [*Message envoyé*],              [*Réponse serveur*],
  [Client],      [`"x y r g b"`],                  [`"OK"` ou `"error: ..."`],
  [Client],      [`"size"`],                        [`"W H"`],
  [Displayer],   [connexion sur `port + 1`],        [`"W H"`, pixels, `"END"`],
  [Displayer],   [(connexion persistante ouverte)], [`"x y r g b"` à chaque update],
)

== Choix d'implémentation

*Principe de responsabilité unique (SRP)*: transport TCP (`Socket`), sérialisation (`Message`), les logiques de `Serveur` et  `Client` sont des couches distinctes

#pause

*Thread-safety*: `ImageEditor` protège `sf::Image` par un `std::mutex` ; les threads réseau et GUI accèdent à l'image.

#pause

*Validation centralisée*: `Serveur::listen_req()` concentre format, couleurs et bornes ; le code appelant reçoit un `Request` garanti valide

= Extension

== Extension: Afficheur à distance

*Description :* un binaire `displayer` se connecte au serveur et affiche le canvas SFML en temps réel, sans modifier le flux client/serveur existant.

*Impact protocole :*
- Port dédié `port + 1`: pas de multiplexage sur le socket principal
- Protocole orienté ligne : `"W H"` → pixels non-blancs → `"END"` → updates continus

*Impact architecture :*
- `DisplayerManager` (serveur): thread d'acceptation, liste de fds, broadcast
- `Displayer` (client): lecture ligne par ligne avec buffer, pas de dépendance à `Message`

= Tests

== Scénarios de test: `pxlwar_client_test <port>`

#table(
  columns: (auto, 1fr, auto),
  stroke: 0.5pt,
  inset: 6pt,
  fill: (_, row) => if row == 0 { luma(215) },
  [*\#*], [*Scénario*],                                        [*Ce qui est validé*],
  [1],    [Récupération de la taille (`size`)],                 [W > 0 et H > 0],
  [2],    [Pixel valide],                                       [`"OK"` reçu],
  [3],    [4 coins du canvas],                                  [`"OK"` × 4],
  [4],    [Coordonnées hors-canvas (x=W, y=H, x=−1)],          [`"error"` + serveur vivant],
  [5],    [Couleurs invalides (> 255, négatives)],              [`"error"` + serveur vivant],
  [6],    [Message malformé],                                   [`"error"` + serveur vivant],
  [7],    [Displayer: canvas initial puis update temps réel],  [pixel reçu en thread séparé],
)

= Démonstration

== Démonstration live

#align(center)[
  #v(1em)
  #block(fill: luma(230), radius: 4pt, inset: 14pt)[
    `cmake . && make` \
    `./build/server <port>` \
    `./build/displayer <port>` \
    `./build/client <port> size` \
    `./build/client <port> x y r g b` \
    `./build/pxlwar_client_test <port>`
  ]
  #v(0.8em)
]

= Bilan

== Bilan & difficultés

*Points forts :*
- Validation du protocole entièrement centralisée dans `listen_req()`
- Thread-safety garantie: pas de problème entre réseau et affichage
- Extension displayer non-intrusive: zéro modification du flux client/serveur existant

*Difficultés rencontrées :*
- Trouver un diagramme de classe satisfaisant
- Trouver quoi tester

*Ce qui reste à améliorer :*
- `Socket::send` fait `exit(1)` sur erreur: pas de récupération gracieuse des déconnexions
