import { downloadTools } from "./tools.ts"
import { downloadLibs } from "./libs.ts";

export async function install() {
    await downloadTools();

    await downloadLibs();
}