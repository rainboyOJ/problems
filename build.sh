node ./src/lib/dataBase_and_render.js
yarn build
make
cp -r ./src/assets/* dist/

# 渲染 about.md等
node ./src/lib/render_other_md.js
