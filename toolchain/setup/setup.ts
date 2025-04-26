import { downloadTools } from "./tools.ts"
import { downloadLibs } from "./libs.ts";

export async function setup() {
    await downloadTools();

    await downloadLibs();
}