const std = @import("std");

// Although this function looks imperative, note that its job is to
// declaratively construct a build graph that will be executed by an external
// runner.
pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    const exe = b.addExecutable(.{
        .name = "matalgo",
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });
    exe.addCSourceFiles(.{ .root = b.path("src"), .files = &.{ "main.c", "matrix.c" }, .flags = &.{ "-Wall", "-ffast-math", "-O3", "-Werror", "-Wno-unused-parameter", "-Wno-unused-variable", "-Wno-unused-function", "-Wno-unused-value", "-Wno-unused-label", "-Wno-unused-but-set-variable", "-Wno-unused-const-variable", "-Wno-unused-local-typedefs", "-Wno-unused-macros" } });
    exe.linkSystemLibrary("m");
    exe.addIncludePath(b.path("includes"));

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
